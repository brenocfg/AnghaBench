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

/* Variables and functions */
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 scalar_t__ rtas_token (char const*) ; 

int rtas_service_present(const char *service)
{
	return rtas_token(service) != RTAS_UNKNOWN_SERVICE;
}