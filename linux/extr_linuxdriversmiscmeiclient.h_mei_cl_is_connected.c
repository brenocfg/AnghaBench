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
struct mei_cl {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ MEI_FILE_CONNECTED ; 

__attribute__((used)) static inline bool mei_cl_is_connected(struct mei_cl *cl)
{
	return  cl->state == MEI_FILE_CONNECTED;
}