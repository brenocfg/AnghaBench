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
typedef  int u32 ;
struct ktd2692_led_config_data {int movie_max_microamp; int max_brightness; int /*<<< orphan*/  flash_max_microamp; } ;

/* Variables and functions */
 int KTD2692_MM_TO_FL_RATIO (int /*<<< orphan*/ ) ; 
 int KTD2692_MOVIE_MODE_CURRENT_LEVELS ; 

__attribute__((used)) static void ktd2692_init_movie_current_max(struct ktd2692_led_config_data *cfg)
{
	u32 offset, step;
	u32 movie_current_microamp;

	offset = KTD2692_MOVIE_MODE_CURRENT_LEVELS;
	step = KTD2692_MM_TO_FL_RATIO(cfg->flash_max_microamp)
		/ KTD2692_MOVIE_MODE_CURRENT_LEVELS;

	do {
		movie_current_microamp = step * offset;
		offset--;
	} while ((movie_current_microamp > cfg->movie_max_microamp) &&
		(offset > 0));

	cfg->max_brightness = offset;
}