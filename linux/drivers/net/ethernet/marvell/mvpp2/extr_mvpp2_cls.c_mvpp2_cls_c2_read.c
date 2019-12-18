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
typedef  int u32 ;
struct mvpp2_cls_c2_entry {int index; int valid; void** attr; void* act; void** tcam; } ;
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
 int MVPP22_CLS_C2_TCAM_INV_BIT ; 
 void* mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

void mvpp2_cls_c2_read(struct mvpp2 *priv, int index,
		       struct mvpp2_cls_c2_entry *c2)
{
	u32 val;
	mvpp2_write(priv, MVPP22_CLS_C2_TCAM_IDX, index);

	c2->index = index;

	c2->tcam[0] = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_DATA0);
	c2->tcam[1] = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_DATA1);
	c2->tcam[2] = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_DATA2);
	c2->tcam[3] = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_DATA3);
	c2->tcam[4] = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_DATA4);

	c2->act = mvpp2_read(priv, MVPP22_CLS_C2_ACT);

	c2->attr[0] = mvpp2_read(priv, MVPP22_CLS_C2_ATTR0);
	c2->attr[1] = mvpp2_read(priv, MVPP22_CLS_C2_ATTR1);
	c2->attr[2] = mvpp2_read(priv, MVPP22_CLS_C2_ATTR2);
	c2->attr[3] = mvpp2_read(priv, MVPP22_CLS_C2_ATTR3);

	val = mvpp2_read(priv, MVPP22_CLS_C2_TCAM_INV);
	c2->valid = !(val & MVPP22_CLS_C2_TCAM_INV_BIT);
}