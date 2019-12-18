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
struct f34_data {int update_status; } ;

/* Variables and functions */
 struct f34_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmi_f34_status(struct rmi_function *fn)
{
	struct f34_data *f34 = dev_get_drvdata(&fn->dev);

	/*
	 * The status is the percentage complete, or once complete,
	 * zero for success or a negative return code.
	 */
	return f34->update_status;
}