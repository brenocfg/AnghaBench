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
struct rtllib_hdr_4addr {int /*<<< orphan*/ * payload; } ;
struct rtllib_hdr_3addr {int /*<<< orphan*/ * payload; } ;
struct rtllib_hdr_2addr {int /*<<< orphan*/ * payload; } ;
struct rtllib_hdr_1addr {int /*<<< orphan*/ * payload; } ;
struct rtllib_hdr {int /*<<< orphan*/  frame_ctl; } ;

/* Variables and functions */
#define  RTLLIB_1ADDR_LEN 131 
#define  RTLLIB_2ADDR_LEN 130 
#define  RTLLIB_3ADDR_LEN 129 
#define  RTLLIB_4ADDR_LEN 128 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int rtllib_get_hdrlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *rtllib_get_payload(struct rtllib_hdr *hdr)
{
	switch (rtllib_get_hdrlen(le16_to_cpu(hdr->frame_ctl))) {
	case RTLLIB_1ADDR_LEN:
		return ((struct rtllib_hdr_1addr *)hdr)->payload;
	case RTLLIB_2ADDR_LEN:
		return ((struct rtllib_hdr_2addr *)hdr)->payload;
	case RTLLIB_3ADDR_LEN:
		return ((struct rtllib_hdr_3addr *)hdr)->payload;
	case RTLLIB_4ADDR_LEN:
		return ((struct rtllib_hdr_4addr *)hdr)->payload;
	}
	return NULL;
}