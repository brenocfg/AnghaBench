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
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static void dispatch_bio_list(struct bio_list *tmp)
{
	struct bio *bio;

	while ((bio = bio_list_pop(tmp)))
		generic_make_request(bio);
}