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
struct pxa168_eth_platform_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pxa168_device_eth ; 
 int pxa_register_device (int /*<<< orphan*/ *,struct pxa168_eth_platform_data*,int) ; 

__attribute__((used)) static inline int pxa168_add_eth(struct pxa168_eth_platform_data *data)
{
	return pxa_register_device(&pxa168_device_eth, data, sizeof(*data));
}