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
struct vibra_info {scalar_t__ enabled; int /*<<< orphan*/  play_work; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct vibra_info* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  sc27xx_vibra_set (struct vibra_info*,int) ; 

__attribute__((used)) static void sc27xx_vibra_close(struct input_dev *input)
{
	struct vibra_info *info = input_get_drvdata(input);

	cancel_work_sync(&info->play_work);
	if (info->enabled)
		sc27xx_vibra_set(info, false);
}