#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  enum debuglevel { ____Placeholder_debuglevel } debuglevel ;
struct TYPE_7__ {int /*<<< orphan*/  Subcommand; int /*<<< orphan*/  Command; int /*<<< orphan*/  ApplId; } ;
typedef  TYPE_1__ _cmsg ;
struct TYPE_8__ {int /*<<< orphan*/  buf; } ;
typedef  TYPE_2__ _cdebbuf ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ___ratelimit (int*,char const*) ; 
 int /*<<< orphan*/  capi_cmd2str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* capi_cmsg2str (TYPE_1__*) ; 
 int /*<<< orphan*/  cdebbuf_free (TYPE_2__*) ; 
 int /*<<< orphan*/  gig_dbg (int,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gigaset_debuglevel ; 
 int msg_dump_ratelimit ; 

__attribute__((used)) static inline void dump_cmsg(enum debuglevel level, const char *tag, _cmsg *p)
{
#ifdef CONFIG_GIGASET_DEBUG
	/* dump at most 20 messages in 20 secs */
	static DEFINE_RATELIMIT_STATE(msg_dump_ratelimit, 20 * HZ, 20);
	_cdebbuf *cdb;

	if (!(gigaset_debuglevel & level))
		return;
	if (!___ratelimit(&msg_dump_ratelimit, tag))
		return;

	cdb = capi_cmsg2str(p);
	if (cdb) {
		gig_dbg(level, "%s: [%d] %s", tag, p->ApplId, cdb->buf);
		cdebbuf_free(cdb);
	} else {
		gig_dbg(level, "%s: [%d] %s", tag, p->ApplId,
			capi_cmd2str(p->Command, p->Subcommand));
	}
#endif
}