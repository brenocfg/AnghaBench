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
struct tb_service_id {int match_flags; scalar_t__ protocol_id; scalar_t__ protocol_version; scalar_t__ protocol_revision; int /*<<< orphan*/  protocol_key; } ;
struct tb_service {scalar_t__ prtcid; scalar_t__ prtcvers; scalar_t__ prtcrevs; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int TBSVC_MATCH_PROTOCOL_ID ; 
 int TBSVC_MATCH_PROTOCOL_KEY ; 
 int TBSVC_MATCH_PROTOCOL_VERSION ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool match_service_id(const struct tb_service_id *id,
			     const struct tb_service *svc)
{
	if (id->match_flags & TBSVC_MATCH_PROTOCOL_KEY) {
		if (strcmp(id->protocol_key, svc->key))
			return false;
	}

	if (id->match_flags & TBSVC_MATCH_PROTOCOL_ID) {
		if (id->protocol_id != svc->prtcid)
			return false;
	}

	if (id->match_flags & TBSVC_MATCH_PROTOCOL_VERSION) {
		if (id->protocol_version != svc->prtcvers)
			return false;
	}

	if (id->match_flags & TBSVC_MATCH_PROTOCOL_VERSION) {
		if (id->protocol_revision != svc->prtcrevs)
			return false;
	}

	return true;
}