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
typedef  enum debuglevel { ____Placeholder_debuglevel } debuglevel ;
typedef  int /*<<< orphan*/  _cmsg ;

/* Variables and functions */

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