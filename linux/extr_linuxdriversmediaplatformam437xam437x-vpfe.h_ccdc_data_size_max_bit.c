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
typedef  int u8 ;
typedef  enum vpfe_ccdc_data_size { ____Placeholder_vpfe_ccdc_data_size } vpfe_ccdc_data_size ;

/* Variables and functions */
 int VPFE_CCDC_DATA_8BITS ; 

__attribute__((used)) static inline u8 ccdc_data_size_max_bit(enum vpfe_ccdc_data_size sz)
{
	return sz == VPFE_CCDC_DATA_8BITS ? 7 : 15 - sz;
}