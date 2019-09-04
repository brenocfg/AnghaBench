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
struct cobalt {char* hdl_info; scalar_t__ bar1; } ;

/* Variables and functions */
 scalar_t__ COBALT_HDL_INFO_BASE ; 
 int COBALT_HDL_INFO_SIZE ; 
 int /*<<< orphan*/  COBALT_HDL_SEARCH_STR ; 
 char ioread8 (scalar_t__) ; 
 scalar_t__ strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cobalt_hdl_info_get(struct cobalt *cobalt)
{
	int i;

	for (i = 0; i < COBALT_HDL_INFO_SIZE; i++)
		cobalt->hdl_info[i] =
			ioread8(cobalt->bar1 + COBALT_HDL_INFO_BASE + i);
	cobalt->hdl_info[COBALT_HDL_INFO_SIZE - 1] = '\0';
	if (strstr(cobalt->hdl_info, COBALT_HDL_SEARCH_STR))
		return 0;

	return 1;
}