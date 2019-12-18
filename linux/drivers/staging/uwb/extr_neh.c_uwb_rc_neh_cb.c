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
struct uwb_rceb {int dummy; } ;
struct uwb_rc_neh {int /*<<< orphan*/  arg; int /*<<< orphan*/  rc; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uwb_rceb*,size_t) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uwb_rceb*,size_t) ; 
 int /*<<< orphan*/  uwb_rc_neh_put (struct uwb_rc_neh*) ; 

__attribute__((used)) static void uwb_rc_neh_cb(struct uwb_rc_neh *neh, struct uwb_rceb *rceb, size_t size)
{
	(*neh->cb)(neh->rc, neh->arg, rceb, size);
	uwb_rc_neh_put(neh);
}