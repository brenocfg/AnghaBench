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
typedef  int /*<<< orphan*/  u32 ;
struct mvpp2_cls_c2_entry {int /*<<< orphan*/ * tcam; int /*<<< orphan*/ * attr; int /*<<< orphan*/  act; scalar_t__ valid; int /*<<< orphan*/  index; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP22_CLS_C2_ACT ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_ATTR0 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_ATTR1 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_ATTR2 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_ATTR3 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_DATA0 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_DATA1 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_DATA2 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_DATA3 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_DATA4 ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_IDX ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_INV ; 
 int /*<<< orphan*/  MVPP22_CLS_C2_TCAM_INV_BIT ; 
 int /*<<< orphan*/  mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_cls_c2_write(struct mvpp2 *priv,
			       struct mvpp2_cls_c2_entry *c2)
{
	u32 val;
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_IDX, c2->index);

	val = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_INV);
	if (c2->valid)
		val &= ~MVPP22_CLS_C2_TCAM_INV_BIT;
	else
		val |= MVPP22_CLS_C2_TCAM_INV_BIT;
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_INV, val);

	mvpp2_write(priv, MVPP22_CLS_C2_ACT, c2->act);

	mvpp2_write(priv, MVPP22_CLS_C2_ATTR0, c2->attr[0]);
	mvpp2_write(priv, MVPP22_CLS_C2_ATTR1, c2->attr[1]);
	mvpp2_write(priv, MVPP22_CLS_C2_ATTR2, c2->attr[2]);
	mvpp2_write(priv, MVPP22_CLS_C2_ATTR3, c2->attr[3]);

	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_DATA0, c2->tcam[0]);
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_DATA1, c2->tcam[1]);
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_DATA2, c2->tcam[2]);
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_DATA3, c2->tcam[3]);
	/* Writing TCAM_DATA4 flushes writes to TCAM_DATA0-4 and INV to HW */
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_DATA4, c2->tcam[4]);
}