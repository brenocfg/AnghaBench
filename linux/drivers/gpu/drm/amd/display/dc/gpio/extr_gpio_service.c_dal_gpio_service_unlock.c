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
typedef  int /*<<< orphan*/  uint32_t ;
struct gpio_service {int /*<<< orphan*/ * busyness; } ;
typedef  enum gpio_result { ____Placeholder_gpio_result } gpio_result ;
typedef  enum gpio_id { ____Placeholder_gpio_id } gpio_id ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int GPIO_RESULT_OK ; 
 int GPIO_RESULT_OPEN_FAILED ; 
 int /*<<< orphan*/  set_pin_free (struct gpio_service*,int,int /*<<< orphan*/ ) ; 

enum gpio_result dal_gpio_service_unlock(
	struct gpio_service *service,
	enum gpio_id id,
	uint32_t en)
{
	if (!service->busyness[id]) {
		ASSERT_CRITICAL(false);
		return GPIO_RESULT_OPEN_FAILED;
	}

	set_pin_free(service, id, en);
	return GPIO_RESULT_OK;
}