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
struct ssc_device {int /*<<< orphan*/  list; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct ssc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssc_sound_dai_remove (struct ssc_device*) ; 
 int /*<<< orphan*/  user_lock ; 

__attribute__((used)) static int ssc_remove(struct platform_device *pdev)
{
	struct ssc_device *ssc = platform_get_drvdata(pdev);

	ssc_sound_dai_remove(ssc);

	spin_lock(&user_lock);
	list_del(&ssc->list);
	spin_unlock(&user_lock);

	return 0;
}