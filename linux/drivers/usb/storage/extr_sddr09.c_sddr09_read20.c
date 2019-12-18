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
struct us_data {int dummy; } ;

/* Variables and functions */
 int sddr09_readX (struct us_data*,int /*<<< orphan*/ ,unsigned long,int,int,unsigned char*,int) ; 

__attribute__((used)) static int
sddr09_read20(struct us_data *us, unsigned long fromaddress,
	      int nr_of_pages, int pageshift, unsigned char *buf, int use_sg) {
	int bulklen = nr_of_pages << pageshift;

	/* The last 8 bits of fromaddress are ignored. */
	return sddr09_readX(us, 0, fromaddress, nr_of_pages, bulklen,
			    buf, use_sg);
}