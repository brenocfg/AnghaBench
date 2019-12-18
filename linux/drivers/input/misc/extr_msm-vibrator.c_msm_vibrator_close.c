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
struct msm_vibrator {int /*<<< orphan*/  worker; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct msm_vibrator* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  msm_vibrator_stop (struct msm_vibrator*) ; 

__attribute__((used)) static void msm_vibrator_close(struct input_dev *input)
{
	struct msm_vibrator *vibrator = input_get_drvdata(input);

	cancel_work_sync(&vibrator->worker);
	msm_vibrator_stop(vibrator);
}