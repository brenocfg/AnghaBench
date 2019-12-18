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
struct pqi_io_request {int raid_bypass; int /*<<< orphan*/ * error_info; scalar_t__ status; int /*<<< orphan*/ * scmd; } ;

/* Variables and functions */

__attribute__((used)) static inline void pqi_reinit_io_request(struct pqi_io_request *io_request)
{
	io_request->scmd = NULL;
	io_request->status = 0;
	io_request->error_info = NULL;
	io_request->raid_bypass = false;
}