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
typedef  int u32 ;
typedef  int u16 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  enum gft_profile_type { ____Placeholder_gft_profile_type } gft_profile_type ;

/* Variables and functions */
 int CAM_LINE_SIZE ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_IP_VERSION ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_IP_VERSION_MASK ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_PF_ID ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_PF_ID_MASK ; 
 int GFT_CAM_LINE_MAPPED_PF_ID_MASK_MASK ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK ; 
 int GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK_MASK ; 
 int /*<<< orphan*/  GFT_CAM_LINE_MAPPED_VALID ; 
 int GFT_PROFILE_IPV4 ; 
 int GFT_PROFILE_IPV6 ; 
 int GFT_PROFILE_TCP_PROTOCOL ; 
 int GFT_PROFILE_TYPE_4_TUPLE ; 
 int GFT_PROFILE_TYPE_IP_DST_ADDR ; 
 int GFT_PROFILE_TYPE_IP_SRC_ADDR ; 
 int GFT_PROFILE_TYPE_L4_DST_PORT ; 
 int GFT_PROFILE_TYPE_TUNNEL_TYPE ; 
 int GFT_PROFILE_UDP_PROTOCOL ; 
 int /*<<< orphan*/  GFT_RAM_LINE_DST_IP ; 
 int /*<<< orphan*/  GFT_RAM_LINE_DST_PORT ; 
 int /*<<< orphan*/  GFT_RAM_LINE_ETHERTYPE ; 
 int /*<<< orphan*/  GFT_RAM_LINE_OVER_IP_PROTOCOL ; 
 int /*<<< orphan*/  GFT_RAM_LINE_SRC_IP ; 
 int /*<<< orphan*/  GFT_RAM_LINE_SRC_PORT ; 
 int /*<<< orphan*/  GFT_RAM_LINE_TUNNEL_DST_PORT ; 
 int /*<<< orphan*/  GFT_RAM_LINE_TUNNEL_ETHERTYPE ; 
 int /*<<< orphan*/  GFT_RAM_LINE_TUNNEL_OVER_IP_PROTOCOL ; 
 int MAX_GFT_PROFILE_TYPE ; 
 int PARSER_ETH_CONN_CM_HDR ; 
 int PRS_GFT_CAM_LINES_NO_MATCH ; 
 scalar_t__ PRS_REG_CM_HDR_GFT ; 
 int PRS_REG_CM_HDR_GFT_CM_HDR_SHIFT ; 
 int PRS_REG_CM_HDR_GFT_EVENT_ID_SHIFT ; 
 scalar_t__ PRS_REG_GFT_CAM ; 
 scalar_t__ PRS_REG_GFT_PROFILE_MASK_RAM ; 
 scalar_t__ PRS_REG_LOAD_L2_FILTER ; 
 scalar_t__ PRS_REG_SEARCH_GFT ; 
 scalar_t__ PRS_REG_SEARCH_NON_IP_AS_GFT ; 
 scalar_t__ PRS_REG_SEARCH_TENANT_ID ; 
 int RAM_LINE_SIZE ; 
 scalar_t__ REG_SIZE ; 
 int /*<<< orphan*/  SET_FIELD (int,int /*<<< orphan*/ ,int) ; 
 int T_ETH_PACKET_MATCH_RFS_EVENTID ; 
 int qed_rd (struct qed_hwfn*,struct qed_ptt*,scalar_t__) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,scalar_t__,int) ; 

void qed_gft_config(struct qed_hwfn *p_hwfn,
		    struct qed_ptt *p_ptt,
		    u16 pf_id,
		    bool tcp,
		    bool udp,
		    bool ipv4, bool ipv6, enum gft_profile_type profile_type)
{
	u32 reg_val, cam_line, ram_line_lo, ram_line_hi, search_non_ip_as_gft;

	if (!ipv6 && !ipv4)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at least on of - ipv4 or ipv6'\n");
	if (!tcp && !udp)
		DP_NOTICE(p_hwfn,
			  "gft_config: must accept at least on of - udp or tcp\n");
	if (profile_type >= MAX_GFT_PROFILE_TYPE)
		DP_NOTICE(p_hwfn, "gft_config: unsupported gft_profile_type\n");

	/* Set RFS event ID to be awakened i Tstorm By Prs */
	reg_val = T_ETH_PACKET_MATCH_RFS_EVENTID <<
		  PRS_REG_CM_HDR_GFT_EVENT_ID_SHIFT;
	reg_val |= PARSER_ETH_CONN_CM_HDR << PRS_REG_CM_HDR_GFT_CM_HDR_SHIFT;
	qed_wr(p_hwfn, p_ptt, PRS_REG_CM_HDR_GFT, reg_val);

	/* Do not load context only cid in PRS on match. */
	qed_wr(p_hwfn, p_ptt, PRS_REG_LOAD_L2_FILTER, 0);

	/* Do not use tenant ID exist bit for gft search */
	qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_TENANT_ID, 0);

	/* Set Cam */
	cam_line = 0;
	SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_VALID, 1);

	/* Filters are per PF!! */
	SET_FIELD(cam_line,
		  GFT_CAM_LINE_MAPPED_PF_ID_MASK,
		  GFT_CAM_LINE_MAPPED_PF_ID_MASK_MASK);
	SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_PF_ID, pf_id);

	if (!(tcp && udp)) {
		SET_FIELD(cam_line,
			  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK,
			  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE_MASK_MASK);
		if (tcp)
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE,
				  GFT_PROFILE_TCP_PROTOCOL);
		else
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_UPPER_PROTOCOL_TYPE,
				  GFT_PROFILE_UDP_PROTOCOL);
	}

	if (!(ipv4 && ipv6)) {
		SET_FIELD(cam_line, GFT_CAM_LINE_MAPPED_IP_VERSION_MASK, 1);
		if (ipv4)
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_IP_VERSION,
				  GFT_PROFILE_IPV4);
		else
			SET_FIELD(cam_line,
				  GFT_CAM_LINE_MAPPED_IP_VERSION,
				  GFT_PROFILE_IPV6);
	}

	/* Write characteristics to cam */
	qed_wr(p_hwfn, p_ptt, PRS_REG_GFT_CAM + CAM_LINE_SIZE * pf_id,
	       cam_line);
	cam_line =
	    qed_rd(p_hwfn, p_ptt, PRS_REG_GFT_CAM + CAM_LINE_SIZE * pf_id);

	/* Write line to RAM - compare to filter 4 tuple */
	ram_line_lo = 0;
	ram_line_hi = 0;

	/* Search no IP as GFT */
	search_non_ip_as_gft = 0;

	/* Tunnel type */
	SET_FIELD(ram_line_lo, GFT_RAM_LINE_TUNNEL_DST_PORT, 1);
	SET_FIELD(ram_line_lo, GFT_RAM_LINE_TUNNEL_OVER_IP_PROTOCOL, 1);

	if (profile_type == GFT_PROFILE_TYPE_4_TUPLE) {
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_DST_IP, 1);
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_SRC_IP, 1);
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_OVER_IP_PROTOCOL, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_ETHERTYPE, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_SRC_PORT, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_DST_PORT, 1);
	} else if (profile_type == GFT_PROFILE_TYPE_L4_DST_PORT) {
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_OVER_IP_PROTOCOL, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_ETHERTYPE, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_DST_PORT, 1);
	} else if (profile_type == GFT_PROFILE_TYPE_IP_DST_ADDR) {
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_DST_IP, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_ETHERTYPE, 1);
	} else if (profile_type == GFT_PROFILE_TYPE_IP_SRC_ADDR) {
		SET_FIELD(ram_line_hi, GFT_RAM_LINE_SRC_IP, 1);
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_ETHERTYPE, 1);
	} else if (profile_type == GFT_PROFILE_TYPE_TUNNEL_TYPE) {
		SET_FIELD(ram_line_lo, GFT_RAM_LINE_TUNNEL_ETHERTYPE, 1);

		/* Allow tunneled traffic without inner IP */
		search_non_ip_as_gft = 1;
	}

	qed_wr(p_hwfn,
	       p_ptt, PRS_REG_SEARCH_NON_IP_AS_GFT, search_non_ip_as_gft);
	qed_wr(p_hwfn,
	       p_ptt,
	       PRS_REG_GFT_PROFILE_MASK_RAM + RAM_LINE_SIZE * pf_id,
	       ram_line_lo);
	qed_wr(p_hwfn,
	       p_ptt,
	       PRS_REG_GFT_PROFILE_MASK_RAM + RAM_LINE_SIZE * pf_id + REG_SIZE,
	       ram_line_hi);

	/* Set default profile so that no filter match will happen */
	qed_wr(p_hwfn,
	       p_ptt,
	       PRS_REG_GFT_PROFILE_MASK_RAM + RAM_LINE_SIZE *
	       PRS_GFT_CAM_LINES_NO_MATCH, 0xffffffff);
	qed_wr(p_hwfn,
	       p_ptt,
	       PRS_REG_GFT_PROFILE_MASK_RAM + RAM_LINE_SIZE *
	       PRS_GFT_CAM_LINES_NO_MATCH + REG_SIZE, 0x3ff);

	/* Enable gft search */
	qed_wr(p_hwfn, p_ptt, PRS_REG_SEARCH_GFT, 1);
}