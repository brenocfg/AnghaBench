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
struct mt_device {int dummy; } ;
struct mt_application {int /*<<< orphan*/  quirks; int /*<<< orphan*/  have_contact_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_QUIRK_CONTACT_CNT_ACCURATE ; 

__attribute__((used)) static void mt_post_parse(struct mt_device *td, struct mt_application *app)
{
	if (!app->have_contact_count)
		app->quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
}