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
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_CLS_FLOW_TBL_HIT_CTR ; 
 int /*<<< orphan*/  MVPP2_CTRS_IDX ; 
 int /*<<< orphan*/  mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

u32 mvpp2_cls_flow_hits(struct mvpp2 *priv, int index)
{
	mvpp2_write(priv, MVPP2_CTRS_IDX, index);

	return mvpp2_read(priv, MVPP2_CLS_FLOW_TBL_HIT_CTR);
}