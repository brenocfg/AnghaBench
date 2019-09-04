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
struct rmi_function {int /*<<< orphan*/  dev; } ;
struct f55_data {struct rmi_function* fn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct f55_data*) ; 
 struct f55_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int rmi_f55_detect (struct rmi_function*) ; 

__attribute__((used)) static int rmi_f55_probe(struct rmi_function *fn)
{
	struct f55_data *f55;

	f55 = devm_kzalloc(&fn->dev, sizeof(struct f55_data), GFP_KERNEL);
	if (!f55)
		return -ENOMEM;

	f55->fn = fn;
	dev_set_drvdata(&fn->dev, f55);

	return rmi_f55_detect(fn);
}