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
struct bio {int dummy; } ;

/* Variables and functions */
 int READ_WRITE_LOCK_LEVEL ; 
 scalar_t__ WRITE ; 
 int WRITE_LOCK_LEVEL ; 
 scalar_t__ bio_data_dir (struct bio*) ; 

__attribute__((used)) static unsigned lock_level(struct bio *bio)
{
	return bio_data_dir(bio) == WRITE ?
		WRITE_LOCK_LEVEL :
		READ_WRITE_LOCK_LEVEL;
}