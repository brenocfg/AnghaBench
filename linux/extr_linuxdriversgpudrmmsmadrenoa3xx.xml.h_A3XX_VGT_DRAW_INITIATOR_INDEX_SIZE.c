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
typedef  int uint32_t ;
typedef  enum pc_di_index_size { ____Placeholder_pc_di_index_size } pc_di_index_size ;

/* Variables and functions */
 int A3XX_VGT_DRAW_INITIATOR_INDEX_SIZE__MASK ; 
 int A3XX_VGT_DRAW_INITIATOR_INDEX_SIZE__SHIFT ; 

__attribute__((used)) static inline uint32_t A3XX_VGT_DRAW_INITIATOR_INDEX_SIZE(enum pc_di_index_size val)
{
	return ((val) << A3XX_VGT_DRAW_INITIATOR_INDEX_SIZE__SHIFT) & A3XX_VGT_DRAW_INITIATOR_INDEX_SIZE__MASK;
}