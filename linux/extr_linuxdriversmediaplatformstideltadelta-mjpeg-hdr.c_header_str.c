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
struct mjpeg_header {int length; int sample_precision; int frame_width; int frame_height; int nb_of_components; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,unsigned int,char*,int,int,int,int,int) ; 

__attribute__((used)) static char *header_str(struct mjpeg_header *header,
			char *str,
			unsigned int len)
{
	char *cur = str;
	unsigned int left = len;

	if (!header)
		return "";

	snprintf(cur, left, "[MJPEG header]\n"
			"|- length     = %d\n"
			"|- precision  = %d\n"
			"|- width      = %d\n"
			"|- height     = %d\n"
			"|- components = %d\n",
			header->length,
			header->sample_precision,
			header->frame_width,
			header->frame_height,
			header->nb_of_components);

	return str;
}