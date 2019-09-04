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
struct rxe_pkt_info {scalar_t__ offset; scalar_t__ hdr; } ;

/* Variables and functions */
 int __bth_becn (scalar_t__) ; 

__attribute__((used)) static inline int bth_becn(struct rxe_pkt_info *pkt)
{
	return __bth_becn(pkt->hdr + pkt->offset);
}