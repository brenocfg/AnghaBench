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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u16 ;
struct zfcp_dbf_pay {int /*<<< orphan*/  counter; int /*<<< orphan*/  data; int /*<<< orphan*/  area; int /*<<< orphan*/  fsf_req_id; } ;
struct zfcp_dbf {int /*<<< orphan*/  pay_lock; int /*<<< orphan*/  pay; struct zfcp_dbf_pay pay_buf; } ;

/* Variables and functions */
 scalar_t__ ZFCP_DBF_PAY_MAX_REC ; 
 int /*<<< orphan*/  ZFCP_DBF_TAG_LEN ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct zfcp_dbf_pay*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct zfcp_dbf_pay*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_plen (scalar_t__) ; 

__attribute__((used)) static inline
void zfcp_dbf_pl_write(struct zfcp_dbf *dbf, void *data, u16 length, char *area,
		       u64 req_id)
{
	struct zfcp_dbf_pay *pl = &dbf->pay_buf;
	u16 offset = 0, rec_length;

	spin_lock(&dbf->pay_lock);
	memset(pl, 0, sizeof(*pl));
	pl->fsf_req_id = req_id;
	memcpy(pl->area, area, ZFCP_DBF_TAG_LEN);

	while (offset < length) {
		rec_length = min((u16) ZFCP_DBF_PAY_MAX_REC,
				 (u16) (length - offset));
		memcpy(pl->data, data + offset, rec_length);
		debug_event(dbf->pay, 1, pl, zfcp_dbf_plen(rec_length));

		offset += rec_length;
		pl->counter++;
	}

	spin_unlock(&dbf->pay_lock);
}