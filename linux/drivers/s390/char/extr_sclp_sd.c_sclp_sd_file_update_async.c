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
struct sclp_sd_file {int dummy; } ;
typedef  int /*<<< orphan*/  async_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  sclp_sd_file_update (struct sclp_sd_file*) ; 

__attribute__((used)) static void sclp_sd_file_update_async(void *data, async_cookie_t cookie)
{
	struct sclp_sd_file *sd_file = data;

	sclp_sd_file_update(sd_file);
}