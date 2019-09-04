#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rmi_function {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char const* product_id; } ;
struct f01_data {TYPE_1__ properties; } ;

/* Variables and functions */
 struct f01_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 

const char *rmi_f01_get_product_ID(struct rmi_function *fn)
{
	struct f01_data *f01 = dev_get_drvdata(&fn->dev);

	return f01->properties.product_id;
}