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
typedef  unsigned char u8 ;
struct pkt_file {int /*<<< orphan*/  pkt; } ;
struct pkt_attrib {int ether_type; int priority; int /*<<< orphan*/  subtype; int /*<<< orphan*/  hdrlen; } ;
struct iphdr {int tos; } ;
struct ethhdr {int dummy; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  ip_hdr ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  WIFI_QOS_DATA_TYPE ; 
 int /*<<< orphan*/  WLAN_HDR_A3_QOS_LEN ; 
 int /*<<< orphan*/  _rtw_open_pktfile (int /*<<< orphan*/ ,struct pkt_file*) ; 
 int /*<<< orphan*/  _rtw_pktfile_read (struct pkt_file*,unsigned char*,int) ; 

__attribute__((used)) static void set_qos(struct pkt_file *ppktfile, struct pkt_attrib *pattrib)
{
	struct ethhdr etherhdr;
	struct iphdr ip_hdr;
	s32 UserPriority = 0;


	_rtw_open_pktfile(ppktfile->pkt, ppktfile);
	_rtw_pktfile_read(ppktfile, (unsigned char *)&etherhdr, ETH_HLEN);

	/*  get UserPriority from IP hdr */
	if (pattrib->ether_type == 0x0800) {
		_rtw_pktfile_read(ppktfile, (u8 *)&ip_hdr, sizeof(ip_hdr));
/* 		UserPriority = (ntohs(ip_hdr.tos) >> 5) & 0x3; */
		UserPriority = ip_hdr.tos >> 5;
	}
	pattrib->priority = UserPriority;
	pattrib->hdrlen = WLAN_HDR_A3_QOS_LEN;
	pattrib->subtype = WIFI_QOS_DATA_TYPE;
}