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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct snic_io_hdr {int /*<<< orphan*/  init_ctx; int /*<<< orphan*/  cmnd_id; int /*<<< orphan*/  hid; int /*<<< orphan*/  status; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
snic_io_hdr_dec(struct snic_io_hdr *hdr, u8 *typ, u8 *stat, u32 *cmnd_id,
		u32 *hid, ulong *ctx)
{
	*typ = hdr->type;
	*stat = hdr->status;
	*hid = le32_to_cpu(hdr->hid);
	*cmnd_id = le32_to_cpu(hdr->cmnd_id);
	*ctx = hdr->init_ctx;
}