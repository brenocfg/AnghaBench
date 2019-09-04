#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sh_keysc_info {scalar_t__ kycr2_delay; } ;
struct sh_keysc_priv {struct sh_keysc_info pdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  KYCR2 ; 
 unsigned long KYCR2_IRQ_LEVEL ; 
 int /*<<< orphan*/  KYOUTDR ; 
 int /*<<< orphan*/  sh_keysc_write (struct sh_keysc_priv*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void sh_keysc_level_mode(struct sh_keysc_priv *p,
				unsigned long keys_set)
{
	struct sh_keysc_info *pdata = &p->pdata;

	sh_keysc_write(p, KYOUTDR, 0);
	sh_keysc_write(p, KYCR2, KYCR2_IRQ_LEVEL | (keys_set << 8));

	if (pdata->kycr2_delay)
		udelay(pdata->kycr2_delay);
}