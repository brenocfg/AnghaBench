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
struct adb_request {void (* done ) (struct adb_request*) ;int complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 
 void stub1 (struct adb_request*) ; 

__attribute__((used)) static inline void
pmu_done(struct adb_request *req)
{
	void (*done)(struct adb_request *) = req->done;
	mb();
	req->complete = 1;
    	/* Here, we assume that if the request has a done member, the
    	 * struct request will survive to setting req->complete to 1
    	 */
	if (done)
		(*done)(req);
}