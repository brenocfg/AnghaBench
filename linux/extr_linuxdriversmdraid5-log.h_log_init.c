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
struct r5conf {int dummy; } ;
struct md_rdev {int dummy; } ;

/* Variables and functions */
 int ppl_init_log (struct r5conf*) ; 
 int r5l_init_log (struct r5conf*,struct md_rdev*) ; 

__attribute__((used)) static inline int log_init(struct r5conf *conf, struct md_rdev *journal_dev,
			   bool ppl)
{
	if (journal_dev)
		return r5l_init_log(conf, journal_dev);
	else if (ppl)
		return ppl_init_log(conf);

	return 0;
}