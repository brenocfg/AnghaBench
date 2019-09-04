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
struct v4l2_mbus_framefmt {int width; int height; scalar_t__ code; } ;
struct et8ek8_reglist {scalar_t__ type; } ;
struct et8ek8_meta_reglist {int dummy; } ;

/* Variables and functions */
 scalar_t__ ET8EK8_REGLIST_MODE ; 
 struct et8ek8_reglist** et8ek8_reglist_first (struct et8ek8_meta_reglist*) ; 
 int /*<<< orphan*/  et8ek8_reglist_to_mbus (struct et8ek8_reglist*,struct v4l2_mbus_framefmt*) ; 
 unsigned int min (int,int) ; 

__attribute__((used)) static struct et8ek8_reglist *et8ek8_reglist_find_mode_fmt(
		struct et8ek8_meta_reglist *meta,
		struct v4l2_mbus_framefmt *fmt)
{
	struct et8ek8_reglist **list = et8ek8_reglist_first(meta);
	struct et8ek8_reglist *best_match = NULL;
	struct et8ek8_reglist *best_other = NULL;
	struct v4l2_mbus_framefmt format;
	unsigned int max_dist_match = (unsigned int)-1;
	unsigned int max_dist_other = (unsigned int)-1;

	/*
	 * Find the mode with the closest image size. The distance between
	 * image sizes is the size in pixels of the non-overlapping regions
	 * between the requested size and the frame-specified size.
	 *
	 * Store both the closest mode that matches the requested format, and
	 * the closest mode for all other formats. The best match is returned
	 * if found, otherwise the best mode with a non-matching format is
	 * returned.
	 */
	for (; *list; list++) {
		unsigned int dist;

		if ((*list)->type != ET8EK8_REGLIST_MODE)
			continue;

		et8ek8_reglist_to_mbus(*list, &format);

		dist = min(fmt->width, format.width)
		     * min(fmt->height, format.height);
		dist = format.width * format.height
		     + fmt->width * fmt->height - 2 * dist;


		if (fmt->code == format.code) {
			if (dist < max_dist_match || !best_match) {
				best_match = *list;
				max_dist_match = dist;
			}
		} else {
			if (dist < max_dist_other || !best_other) {
				best_other = *list;
				max_dist_other = dist;
			}
		}
	}

	return best_match ? best_match : best_other;
}