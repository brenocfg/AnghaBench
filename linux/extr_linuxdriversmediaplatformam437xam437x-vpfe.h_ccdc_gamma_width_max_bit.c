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
typedef  enum vpfe_ccdc_gamma_width { ____Placeholder_vpfe_ccdc_gamma_width } vpfe_ccdc_gamma_width ;

/* Variables and functions */

__attribute__((used)) static inline u8 ccdc_gamma_width_max_bit(enum vpfe_ccdc_gamma_width width)
{
	return 15 - width;
}