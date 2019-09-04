#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct gfar_private {int dummy; } ;
struct filer_table {int index; TYPE_1__* fe; } ;
struct TYPE_2__ {int ctrl; int prop; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_FILER_IDX ; 
 int /*<<< orphan*/  gfar_write_filer (struct gfar_private*,int,int,int) ; 

__attribute__((used)) static int gfar_write_filer_table(struct gfar_private *priv,
				  struct filer_table *tab)
{
	u32 i = 0;
	if (tab->index > MAX_FILER_IDX - 1)
		return -EBUSY;

	/* Fill regular entries */
	for (; i < MAX_FILER_IDX && (tab->fe[i].ctrl | tab->fe[i].prop); i++)
		gfar_write_filer(priv, i, tab->fe[i].ctrl, tab->fe[i].prop);
	/* Fill the rest with fall-troughs */
	for (; i < MAX_FILER_IDX; i++)
		gfar_write_filer(priv, i, 0x60, 0xFFFFFFFF);
	/* Last entry must be default accept
	 * because that's what people expect
	 */
	gfar_write_filer(priv, i, 0x20, 0x0);

	return 0;
}