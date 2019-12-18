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
struct mt_application {int /*<<< orphan*/  quirks; int /*<<< orphan*/  mt_usages; } ;
typedef  int /*<<< orphan*/  __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  MT_QUIRK_ALWAYS_VALID ; 
 int /*<<< orphan*/  MT_QUIRK_CONTACT_CNT_ACCURATE ; 
 int /*<<< orphan*/  MT_QUIRK_NOT_SEEN_MEANS_UP ; 
 int /*<<< orphan*/  MT_QUIRK_VALID_IS_CONFIDENCE ; 
 int /*<<< orphan*/  MT_QUIRK_VALID_IS_INRANGE ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt_post_parse_default_settings(struct mt_device *td,
					   struct mt_application *app)
{
	__s32 quirks = app->quirks;

	/* unknown serial device needs special quirks */
	if (list_is_singular(&app->mt_usages)) {
		quirks |= MT_QUIRK_ALWAYS_VALID;
		quirks &= ~MT_QUIRK_NOT_SEEN_MEANS_UP;
		quirks &= ~MT_QUIRK_VALID_IS_INRANGE;
		quirks &= ~MT_QUIRK_VALID_IS_CONFIDENCE;
		quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
	}

	app->quirks = quirks;
}