#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int MAX_UART_INSTANCES ; 
 int /*<<< orphan*/  alias_bitmap ; 
 int /*<<< orphan*/  alias_bitmap_initialized ; 
 int /*<<< orphan*/  bitmap ; 
 int /*<<< orphan*/  bitmap_lock ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdns_uart_of_match ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_1__*,char*) ; 
 int find_next_zero_bit (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_alias_get_alias_list (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int of_alias_get_id (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_and_set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns_get_id(struct platform_device *pdev)
{
	int id, ret;

	mutex_lock(&bitmap_lock);

	/* Alias list is stable that's why get alias bitmap only once */
	if (!alias_bitmap_initialized) {
		ret = of_alias_get_alias_list(cdns_uart_of_match, "serial",
					      alias_bitmap, MAX_UART_INSTANCES);
		if (ret && ret != -EOVERFLOW) {
			mutex_unlock(&bitmap_lock);
			return ret;
		}

		alias_bitmap_initialized++;
	}

	/* Make sure that alias ID is not taken by instance without alias */
	bitmap_or(bitmap, bitmap, alias_bitmap, MAX_UART_INSTANCES);

	dev_dbg(&pdev->dev, "Alias bitmap: %*pb\n",
		MAX_UART_INSTANCES, bitmap);

	/* Look for a serialN alias */
	id = of_alias_get_id(pdev->dev.of_node, "serial");
	if (id < 0) {
		dev_warn(&pdev->dev,
			 "No serial alias passed. Using the first free id\n");

		/*
		 * Start with id 0 and check if there is no serial0 alias
		 * which points to device which is compatible with this driver.
		 * If alias exists then try next free position.
		 */
		id = 0;

		for (;;) {
			dev_info(&pdev->dev, "Checking id %d\n", id);
			id = find_next_zero_bit(bitmap, MAX_UART_INSTANCES, id);

			/* No free empty instance */
			if (id == MAX_UART_INSTANCES) {
				dev_err(&pdev->dev, "No free ID\n");
				mutex_unlock(&bitmap_lock);
				return -EINVAL;
			}

			dev_dbg(&pdev->dev, "The empty id is %d\n", id);
			/* Check if ID is empty */
			if (!test_and_set_bit(id, bitmap)) {
				/* Break the loop if bit is taken */
				dev_dbg(&pdev->dev,
					"Selected ID %d allocation passed\n",
					id);
				break;
			}
			dev_dbg(&pdev->dev,
				"Selected ID %d allocation failed\n", id);
			/* if taking bit fails then try next one */
			id++;
		}
	}

	mutex_unlock(&bitmap_lock);

	return id;
}