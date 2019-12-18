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
typedef  int /*<<< orphan*/  u8 ;
struct rxe_pkt_info {scalar_t__ offset; scalar_t__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bth_pad (scalar_t__) ; 

__attribute__((used)) static inline u8 bth_pad(struct rxe_pkt_info *pkt)
{
	return __bth_pad(pkt->hdr + pkt->offset);
}