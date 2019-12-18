#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* lip; unsigned int* fip; int /*<<< orphan*/  fport; int /*<<< orphan*/  lport; int /*<<< orphan*/  proto; int /*<<< orphan*/  tos; int /*<<< orphan*/  frag; int /*<<< orphan*/  ovlan; int /*<<< orphan*/  ivlan; int /*<<< orphan*/  ethtype; int /*<<< orphan*/  macidx; int /*<<< orphan*/  matchtype; int /*<<< orphan*/  fcoe; int /*<<< orphan*/  iport; } ;
struct TYPE_3__ {unsigned int* lip; unsigned int* fip; scalar_t__ fport; scalar_t__ lport; scalar_t__ proto; scalar_t__ tos; scalar_t__ frag; scalar_t__ ovlan; scalar_t__ ivlan; scalar_t__ ethtype; scalar_t__ macidx; scalar_t__ matchtype; scalar_t__ fcoe; scalar_t__ iport; } ;
struct ch_filter_specification {TYPE_2__ mask; TYPE_1__ val; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  memset (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_default_mask(struct ch_filter_specification *fs)
{
	unsigned int lip = 0, lip_mask = 0;
	unsigned int fip = 0, fip_mask = 0;
	unsigned int i;

	if (fs->val.iport && !fs->mask.iport)
		fs->mask.iport |= ~0;
	if (fs->val.fcoe && !fs->mask.fcoe)
		fs->mask.fcoe |= ~0;
	if (fs->val.matchtype && !fs->mask.matchtype)
		fs->mask.matchtype |= ~0;
	if (fs->val.macidx && !fs->mask.macidx)
		fs->mask.macidx |= ~0;
	if (fs->val.ethtype && !fs->mask.ethtype)
		fs->mask.ethtype |= ~0;
	if (fs->val.ivlan && !fs->mask.ivlan)
		fs->mask.ivlan |= ~0;
	if (fs->val.ovlan && !fs->mask.ovlan)
		fs->mask.ovlan |= ~0;
	if (fs->val.frag && !fs->mask.frag)
		fs->mask.frag |= ~0;
	if (fs->val.tos && !fs->mask.tos)
		fs->mask.tos |= ~0;
	if (fs->val.proto && !fs->mask.proto)
		fs->mask.proto |= ~0;

	for (i = 0; i < ARRAY_SIZE(fs->val.lip); i++) {
		lip |= fs->val.lip[i];
		lip_mask |= fs->mask.lip[i];
		fip |= fs->val.fip[i];
		fip_mask |= fs->mask.fip[i];
	}

	if (lip && !lip_mask)
		memset(fs->mask.lip, ~0, sizeof(fs->mask.lip));

	if (fip && !fip_mask)
		memset(fs->mask.fip, ~0, sizeof(fs->mask.lip));

	if (fs->val.lport && !fs->mask.lport)
		fs->mask.lport = ~0;
	if (fs->val.fport && !fs->mask.fport)
		fs->mask.fport = ~0;
}