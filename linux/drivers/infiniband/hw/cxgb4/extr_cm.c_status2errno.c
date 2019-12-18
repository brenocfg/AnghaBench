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

/* Variables and functions */
#define  CPL_ERR_ARP_MISS 133 
#define  CPL_ERR_CONN_EXIST 132 
#define  CPL_ERR_CONN_RESET 131 
#define  CPL_ERR_CONN_TIMEDOUT 130 
#define  CPL_ERR_NONE 129 
#define  CPL_ERR_TCAM_FULL 128 
 int EADDRINUSE ; 
 int ECONNRESET ; 
 int EHOSTUNREACH ; 
 int EIO ; 
 int ENOMEM ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int status2errno(int status)
{
	switch (status) {
	case CPL_ERR_NONE:
		return 0;
	case CPL_ERR_CONN_RESET:
		return -ECONNRESET;
	case CPL_ERR_ARP_MISS:
		return -EHOSTUNREACH;
	case CPL_ERR_CONN_TIMEDOUT:
		return -ETIMEDOUT;
	case CPL_ERR_TCAM_FULL:
		return -ENOMEM;
	case CPL_ERR_CONN_EXIST:
		return -EADDRINUSE;
	default:
		return -EIO;
	}
}