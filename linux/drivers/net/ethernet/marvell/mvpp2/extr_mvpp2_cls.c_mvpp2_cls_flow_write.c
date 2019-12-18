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
struct mvpp2_cls_flow_entry {int /*<<< orphan*/ * data; int /*<<< orphan*/  index; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_CLS_FLOW_INDEX_REG ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_TBL0_REG ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_TBL1_REG ; 
 int /*<<< orphan*/  MVPP2_CLS_FLOW_TBL2_REG ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_cls_flow_write(struct mvpp2 *priv,
				 struct mvpp2_cls_flow_entry *fe)
{
	mvpp2_write(priv, MVPP2_CLS_FLOW_INDEX_REG, fe->index);
	mvpp2_write(priv, MVPP2_CLS_FLOW_TBL0_REG, fe->data[0]);
	mvpp2_write(priv, MVPP2_CLS_FLOW_TBL1_REG, fe->data[1]);
	mvpp2_write(priv, MVPP2_CLS_FLOW_TBL2_REG, fe->data[2]);
}