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
struct per_bio_data {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct per_bio_data* dm_per_bio_data (struct bio*,int) ; 

__attribute__((used)) static struct per_bio_data *get_per_bio_data(struct bio *bio)
{
	struct per_bio_data *pb = dm_per_bio_data(bio, sizeof(struct per_bio_data));
	BUG_ON(!pb);
	return pb;
}