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
typedef  int /*<<< orphan*/  u64 ;
struct xlr_net_priv {void* class_3_spill; void* class_2_spill; void* class_1_spill; void* class_0_spill; void* frout_spill; void* frin_spill; } ;

/* Variables and functions */
 int MAX_CLASS_0_SPILL ; 
 int MAX_CLASS_1_SPILL ; 
 int MAX_CLASS_2_SPILL ; 
 int MAX_CLASS_3_SPILL ; 
 int MAX_FRIN_SPILL ; 
 int MAX_FROUT_SPILL ; 
 int /*<<< orphan*/  R_CLASS0_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_CLASS0_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_CLASS0_SPILL_MEM_START_1 ; 
 int /*<<< orphan*/  R_CLASS1_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_CLASS1_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_CLASS1_SPILL_MEM_START_1 ; 
 int /*<<< orphan*/  R_CLASS2_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_CLASS2_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_CLASS2_SPILL_MEM_START_1 ; 
 int /*<<< orphan*/  R_CLASS3_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_CLASS3_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_CLASS3_SPILL_MEM_START_1 ; 
 int /*<<< orphan*/  R_FROUT_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_FROUT_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_FROUT_SPILL_MEM_START_1 ; 
 int /*<<< orphan*/  R_REG_FRIN_SPILL_MEM_SIZE ; 
 int /*<<< orphan*/  R_REG_FRIN_SPILL_MEM_START_0 ; 
 int /*<<< orphan*/  R_REG_FRIN_SPILL_MEM_START_1 ; 
 void* xlr_config_spill (struct xlr_net_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlr_config_fifo_spill_area(struct xlr_net_priv *priv)
{
	priv->frin_spill = xlr_config_spill(priv,
					    R_REG_FRIN_SPILL_MEM_START_0,
					    R_REG_FRIN_SPILL_MEM_START_1,
					    R_REG_FRIN_SPILL_MEM_SIZE,
					    MAX_FRIN_SPILL * sizeof(u64));
	priv->frout_spill = xlr_config_spill(priv,
					     R_FROUT_SPILL_MEM_START_0,
					     R_FROUT_SPILL_MEM_START_1,
					     R_FROUT_SPILL_MEM_SIZE,
					     MAX_FROUT_SPILL * sizeof(u64));
	priv->class_0_spill = xlr_config_spill(priv,
					       R_CLASS0_SPILL_MEM_START_0,
					       R_CLASS0_SPILL_MEM_START_1,
					       R_CLASS0_SPILL_MEM_SIZE,
					       MAX_CLASS_0_SPILL * sizeof(u64));
	priv->class_1_spill = xlr_config_spill(priv,
					       R_CLASS1_SPILL_MEM_START_0,
					       R_CLASS1_SPILL_MEM_START_1,
					       R_CLASS1_SPILL_MEM_SIZE,
					       MAX_CLASS_1_SPILL * sizeof(u64));
	priv->class_2_spill = xlr_config_spill(priv,
					       R_CLASS2_SPILL_MEM_START_0,
					       R_CLASS2_SPILL_MEM_START_1,
					       R_CLASS2_SPILL_MEM_SIZE,
					       MAX_CLASS_2_SPILL * sizeof(u64));
	priv->class_3_spill = xlr_config_spill(priv,
					       R_CLASS3_SPILL_MEM_START_0,
					       R_CLASS3_SPILL_MEM_START_1,
					       R_CLASS3_SPILL_MEM_SIZE,
					       MAX_CLASS_3_SPILL * sizeof(u64));
}