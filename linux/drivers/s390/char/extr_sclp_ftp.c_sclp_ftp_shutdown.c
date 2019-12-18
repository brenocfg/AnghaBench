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
 int /*<<< orphan*/  sclp_ftp_event ; 
 int /*<<< orphan*/  sclp_unregister (int /*<<< orphan*/ *) ; 

void sclp_ftp_shutdown(void)
{
	sclp_unregister(&sclp_ftp_event);
}