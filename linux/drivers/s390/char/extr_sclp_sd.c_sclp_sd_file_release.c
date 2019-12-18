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
struct sclp_sd_file {int /*<<< orphan*/  data; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sclp_sd_file*) ; 
 int /*<<< orphan*/  sclp_sd_data_reset (int /*<<< orphan*/ *) ; 
 struct sclp_sd_file* to_sd_file (struct kobject*) ; 

__attribute__((used)) static void sclp_sd_file_release(struct kobject *kobj)
{
	struct sclp_sd_file *sd_file = to_sd_file(kobj);

	sclp_sd_data_reset(&sd_file->data);
	kfree(sd_file);
}