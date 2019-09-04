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
typedef  int u16 ;
struct kempld_device_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEMPLD_GPIO_EVT_LVL_EDGE ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int kempld_read16 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_write16 (struct kempld_device_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kempld_gpio_pincount(struct kempld_device_data *pld)
{
	u16 evt, evt_back;

	kempld_get_mutex(pld);

	/* Backup event register as it might be already initialized */
	evt_back = kempld_read16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);
	/* Clear event register */
	kempld_write16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, 0x0000);
	/* Read back event register */
	evt = kempld_read16(pld, KEMPLD_GPIO_EVT_LVL_EDGE);
	/* Restore event register */
	kempld_write16(pld, KEMPLD_GPIO_EVT_LVL_EDGE, evt_back);

	kempld_release_mutex(pld);

	return evt ? __ffs(evt) : 16;
}