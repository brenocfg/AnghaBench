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
struct ses_device {int /*<<< orphan*/ * page2; } ;
struct enclosure_device {struct ses_device* scratch; } ;

/* Variables and functions */

__attribute__((used)) static bool ses_page2_supported(struct enclosure_device *edev)
{
	struct ses_device *ses_dev = edev->scratch;

	return (ses_dev->page2 != NULL);
}