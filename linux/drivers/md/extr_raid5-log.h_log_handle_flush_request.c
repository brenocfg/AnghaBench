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
struct r5conf {scalar_t__ log; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ppl_handle_flush_request (scalar_t__,struct bio*) ; 
 int r5l_handle_flush_request (scalar_t__,struct bio*) ; 
 scalar_t__ raid5_has_ppl (struct r5conf*) ; 

__attribute__((used)) static inline int log_handle_flush_request(struct r5conf *conf, struct bio *bio)
{
	int ret = -ENODEV;

	if (conf->log)
		ret = r5l_handle_flush_request(conf->log, bio);
	else if (raid5_has_ppl(conf))
		ret = ppl_handle_flush_request(conf->log, bio);

	return ret;
}