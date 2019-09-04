#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mc_request {int dummy; } ;
struct TYPE_2__ {char* sysname; char* nodename; char* release; char* version; char* machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  mconsole_reply (struct mc_request*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*,char*) ; 
 TYPE_1__* utsname () ; 

void mconsole_version(struct mc_request *req)
{
	char version[256];

	sprintf(version, "%s %s %s %s %s", utsname()->sysname,
		utsname()->nodename, utsname()->release, utsname()->version,
		utsname()->machine);
	mconsole_reply(req, version, 0, 0);
}