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
typedef  scalar_t__ uint32_t ;
struct rtas_error_log {int dummy; } ;

/* Variables and functions */
 scalar_t__ rtas_error_extended (struct rtas_error_log*) ; 
 scalar_t__ rtas_error_extended_log_length (struct rtas_error_log*) ; 
 int rtas_error_log_max ; 
 int rtas_get_error_log_max () ; 

__attribute__((used)) static int log_rtas_len(char * buf)
{
	int len;
	struct rtas_error_log *err;
	uint32_t extended_log_length;

	/* rtas fixed header */
	len = 8;
	err = (struct rtas_error_log *)buf;
	extended_log_length = rtas_error_extended_log_length(err);
	if (rtas_error_extended(err) && extended_log_length) {

		/* extended header */
		len += extended_log_length;
	}

	if (rtas_error_log_max == 0)
		rtas_error_log_max = rtas_get_error_log_max();

	if (len > rtas_error_log_max)
		len = rtas_error_log_max;

	return len;
}