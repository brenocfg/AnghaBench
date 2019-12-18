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
struct libipw_hdr_4addr {int /*<<< orphan*/ * payload; } ;
struct libipw_hdr_3addr {int /*<<< orphan*/ * payload; } ;
struct libipw_hdr_2addr {int /*<<< orphan*/ * payload; } ;
struct libipw_hdr_1addr {int /*<<< orphan*/ * payload; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
#define  LIBIPW_1ADDR_LEN 131 
#define  LIBIPW_2ADDR_LEN 130 
#define  LIBIPW_3ADDR_LEN 129 
#define  LIBIPW_4ADDR_LEN 128 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int libipw_get_hdrlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *libipw_get_payload(struct ieee80211_hdr *hdr)
{
	switch (libipw_get_hdrlen(le16_to_cpu(hdr->frame_control))) {
	case LIBIPW_1ADDR_LEN:
		return ((struct libipw_hdr_1addr *)hdr)->payload;
	case LIBIPW_2ADDR_LEN:
		return ((struct libipw_hdr_2addr *)hdr)->payload;
	case LIBIPW_3ADDR_LEN:
		return ((struct libipw_hdr_3addr *)hdr)->payload;
	case LIBIPW_4ADDR_LEN:
		return ((struct libipw_hdr_4addr *)hdr)->payload;
	}
	return NULL;
}