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
typedef  enum intel_pipe_crc_source { ____Placeholder_intel_pipe_crc_source } intel_pipe_crc_source ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int INTEL_PIPE_CRC_SOURCE_NONE ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pipe_crc_sources ; 

__attribute__((used)) static int
display_crc_ctl_parse_source(const char *buf, enum intel_pipe_crc_source *s)
{
	int i;

	if (!buf) {
		*s = INTEL_PIPE_CRC_SOURCE_NONE;
		return 0;
	}

	i = match_string(pipe_crc_sources, ARRAY_SIZE(pipe_crc_sources), buf);
	if (i < 0)
		return i;

	*s = i;
	return 0;
}