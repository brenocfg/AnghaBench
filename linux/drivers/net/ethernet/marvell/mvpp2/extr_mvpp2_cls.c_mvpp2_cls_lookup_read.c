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
struct mvpp2_cls_lookup_entry {int way; int lkpid; int /*<<< orphan*/  data; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_CLS_LKP_INDEX_REG ; 
 int MVPP2_CLS_LKP_INDEX_WAY_OFFS ; 
 int /*<<< orphan*/  MVPP2_CLS_LKP_TBL_REG ; 
 int /*<<< orphan*/  mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

void mvpp2_cls_lookup_read(struct mvpp2 *priv, int lkpid, int way,
			   struct mvpp2_cls_lookup_entry *le)
{
	u32 val;

	val = (way << MVPP2_CLS_LKP_INDEX_WAY_OFFS) | lkpid;
	mvpp2_write(priv, MVPP2_CLS_LKP_INDEX_REG, val);
	le->way = way;
	le->lkpid = lkpid;
	le->data = mvpp2_read(priv, MVPP2_CLS_LKP_TBL_REG);
}