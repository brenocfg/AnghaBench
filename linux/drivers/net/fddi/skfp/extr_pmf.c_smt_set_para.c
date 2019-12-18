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
struct smt_para {int p_len; int p_type; } ;
struct TYPE_4__ {int please_reconnect; } ;
struct fddi_mib {int fddiSMTConfigPolicy; int fddiSMTConnectionPolicy; int fddiSMTTT_Notify; int fddiSMTStatRptPolicy; int fddiSMTTrace_MaxExpiration; long fddiESSPayload; long fddiESSOverhead; int fddiESSMaxTNeg; int fddiESSMinSegmentSize; int fddiESSCategory; int fddiESSSynchTxMode; int fddiSBACommand; int fddiSBAAvailable; struct fddi_mib_p* p; struct fddi_mib_a* a; struct fddi_mib_m* m; } ;
struct TYPE_3__ {void* raf_act_timer_poll; } ;
struct s_smc {TYPE_2__ sm; struct fddi_mib mib; TYPE_1__ ess; } ;
struct s_p_tab {int p_access; int p_offset; char* p_swap; } ;
struct fddi_mib_p {int fddiPORTConnectionPolicies; int fddiPORTMaint_LS; int fddiPORTLer_Cutoff; int fddiPORTLer_Alarm; scalar_t__ fddiPORTRequestedPaths; } ;
struct fddi_mib_m {int fddiMACRequestedPaths; int fddiMACFrameErrorThreshold; int fddiMACNotCopiedThreshold; int fddiMACMA_UnitdataEnable; int fddiMACT_Min; } ;
struct fddi_mib_a {int fddiPATHSbaPayload; int fddiPATHSbaOverhead; long fddiPATHT_Rmode; int fddiPATHSbaAvailable; int fddiPATHTVXLowerBound; int fddiPATHT_MaxLowerBound; int fddiPATHMaxT_Req; } ;

/* Variables and functions */
#define  AC_GR 163 
#define  AC_S 162 
 int /*<<< orphan*/  EC_DISCONNECT ; 
 int /*<<< orphan*/  EVENT_ECM ; 
 int /*<<< orphan*/  EVENT_RMT ; 
 int /*<<< orphan*/  IFSET (int) ; 
 int INDEX_MAC ; 
 int INDEX_PATH ; 
 int INDEX_PORT ; 
 int MIB_P_PATH_PRIM_ALTER ; 
 int MIB_P_PATH_PRIM_PREFER ; 
 long MS2BCLK (int) ; 
 int NUMMACS ; 
 int NUMPATHS ; 
 int POLICY_MM ; 
 int /*<<< orphan*/  RM_ENABLE_FLAG ; 
 int /*<<< orphan*/  RS_EVENT ; 
 int /*<<< orphan*/  RS_SET (struct s_smc*,int /*<<< orphan*/ ) ; 
 int SB_START ; 
 int SB_STOP ; 
 int /*<<< orphan*/  SK_LOC_DECL (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  SMT_E0120 ; 
 int /*<<< orphan*/  SMT_E0120_MSG ; 
#define  SMT_P101A 161 
#define  SMT_P101B 160 
#define  SMT_P101D 159 
#define  SMT_P101E 158 
#define  SMT_P101F 157 
#define  SMT_P103C 156 
#define  SMT_P10F0 155 
#define  SMT_P10F1 154 
#define  SMT_P10F2 153 
#define  SMT_P10F3 152 
#define  SMT_P10F4 151 
#define  SMT_P10F5 150 
#define  SMT_P10F6 149 
#define  SMT_P10F7 148 
#define  SMT_P10F8 147 
#define  SMT_P10F9 146 
#define  SMT_P2020 145 
#define  SMT_P205F 144 
#define  SMT_P2067 143 
#define  SMT_P2076 142 
#define  SMT_P20F1 141 
#define  SMT_P320F 140 
#define  SMT_P3210 139 
#define  SMT_P3213 138 
#define  SMT_P3214 137 
#define  SMT_P3215 136 
#define  SMT_P3216 135 
#define  SMT_P3217 134 
#define  SMT_P400E 133 
#define  SMT_P4011 132 
#define  SMT_P401F 131 
#define  SMT_P403A 130 
#define  SMT_P403B 129 
#define  SMT_P4046 128 
 int /*<<< orphan*/  SMT_PANIC (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMT_PORT_ACTION ; 
 int SMT_RDF_AUTHOR ; 
 int SMT_RDF_ILLEGAL ; 
 int SMT_RDF_LENGTH ; 
 int SMT_RDF_NOPARAM ; 
 int SMT_RDF_RANGE ; 
 int /*<<< orphan*/  SMT_STATION_ACTION ; 
 void* TRUE ; 
 int byte_val ; 
 int /*<<< orphan*/  ess_para_change (struct s_smc*) ; 
 long long_val ; 
 int memcpy (char*,char*,int) ; 
 size_t port_to_mib (struct s_smc*,int) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtm_set_timer (struct s_smc*) ; 
 int /*<<< orphan*/  smt_action (struct s_smc*,int /*<<< orphan*/ ,int,size_t) ; 
 struct s_p_tab* smt_get_ptab (int) ; 
 int smt_mib_phys (struct s_smc*) ; 
 int /*<<< orphan*/  smt_set_mac_opvalues (struct s_smc*) ; 
 int /*<<< orphan*/  u_char ; 
 int /*<<< orphan*/  u_long ; 
 int /*<<< orphan*/  u_short ; 
 int word_val ; 

__attribute__((used)) static int smt_set_para(struct s_smc *smc, struct smt_para *pa, int index,
			int local, int set)
{
#define IFSET(x)	if (set) (x)

	const struct s_p_tab	*pt ;
	int		len ;
	char		*from ;
	char		*to ;
	const char	*swap ;
	char		c ;
	char		*mib_addr ;
	struct fddi_mib	*mib ;
	struct fddi_mib_m	*mib_m = NULL;
	struct fddi_mib_a	*mib_a = NULL;
	struct fddi_mib_p	*mib_p = NULL;
	int		mac ;
	int		path ;
	int		port ;
	SK_LOC_DECL(u_char,byte_val) ;
	SK_LOC_DECL(u_short,word_val) ;
	SK_LOC_DECL(u_long,long_val) ;

	mac = index - INDEX_MAC ;
	path = index - INDEX_PATH ;
	port = index - INDEX_PORT ;
	len = pa->p_len ;
	from = (char *) (pa + 1 ) ;

	mib = &smc->mib ;
	switch (pa->p_type & 0xf000) {
	case 0x1000 :
	default :
		mib_addr = (char *) mib ;
		break ;
	case 0x2000 :
		if (mac < 0 || mac >= NUMMACS) {
			return SMT_RDF_NOPARAM;
		}
		mib_m = &smc->mib.m[mac] ;
		mib_addr = (char *) mib_m ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		break ;
	case 0x3000 :
		if (path < 0 || path >= NUMPATHS) {
			return SMT_RDF_NOPARAM;
		}
		mib_a = &smc->mib.a[path] ;
		mib_addr = (char *) mib_a ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		break ;
	case 0x4000 :
		if (port < 0 || port >= smt_mib_phys(smc)) {
			return SMT_RDF_NOPARAM;
		}
		mib_p = &smc->mib.p[port_to_mib(smc,port)] ;
		mib_addr = (char *) mib_p ;
		from += 4 ;		/* skip index */
		len -= 4 ;
		break ;
	}
	switch (pa->p_type) {
	case SMT_P10F0 :
	case SMT_P10F1 :
#ifdef	ESS
	case SMT_P10F2 :
	case SMT_P10F3 :
	case SMT_P10F4 :
	case SMT_P10F5 :
	case SMT_P10F6 :
	case SMT_P10F7 :
#endif
#ifdef	SBA
	case SMT_P10F8 :
	case SMT_P10F9 :
#endif
	case SMT_P20F1 :
		if (!local)
			return SMT_RDF_NOPARAM;
		break ;
	}
	pt = smt_get_ptab(pa->p_type) ;
	if (!pt)
		return (pa->p_type & 0xff00) ? SMT_RDF_NOPARAM :
					       SMT_RDF_ILLEGAL;
	switch (pt->p_access) {
	case AC_GR :
	case AC_S :
		break ;
	default :
		return SMT_RDF_ILLEGAL;
	}
	to = mib_addr + pt->p_offset ;
	swap = pt->p_swap ;		/* pointer to swap string */

	while (swap && (c = *swap++)) {
		switch(c) {
		case 'b' :
			to = (char *) &byte_val ;
			break ;
		case 'w' :
			to = (char *) &word_val ;
			break ;
		case 'l' :
			to = (char *) &long_val ;
			break ;
		case 'S' :
		case 'E' :
		case 'R' :
		case 'r' :
			if (len < 4) {
				goto len_error ;
			}
			if (from[0] | from[1])
				goto val_error ;
#ifdef	LITTLE_ENDIAN
			if (c == 'r') {
				to[0] = from[2] ;
				to[1] = from[3] ;
			}
			else {
				to[1] = from[2] ;
				to[0] = from[3] ;
			}
#else
			to[0] = from[2] ;
			to[1] = from[3] ;
#endif
			from += 4 ;
			to += 2 ;
			len -= 4 ;
			break ;
		case 'F' :
		case 'B' :
			if (len < 4) {
				goto len_error ;
			}
			if (from[0] | from[1] | from[2])
				goto val_error ;
			to[0] = from[3] ;
			len -= 4 ;
			from += 4 ;
			to += 4 ;
			break ;
		case 'C' :
		case 'T' :
		case 'L' :
			if (len < 4) {
				goto len_error ;
			}
#ifdef	LITTLE_ENDIAN
			to[3] = *from++ ;
			to[2] = *from++ ;
			to[1] = *from++ ;
			to[0] = *from++ ;
#else
			to[0] = *from++ ;
			to[1] = *from++ ;
			to[2] = *from++ ;
			to[3] = *from++ ;
#endif
			len -= 4 ;
			to += 4 ;
			break ;
		case 'A' :
			if (len < 8)
				goto len_error ;
			if (set)
				memcpy(to,from+2,6) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			break ;
		case '4' :
			if (len < 4)
				goto len_error ;
			if (set)
				memcpy(to,from,4) ;
			to += 4 ;
			from += 4 ;
			len -= 4 ;
			break ;
		case '8' :
			if (len < 8)
				goto len_error ;
			if (set)
				memcpy(to,from,8) ;
			to += 8 ;
			from += 8 ;
			len -= 8 ;
			break ;
		case 'D' :
			if (len < 32)
				goto len_error ;
			if (set)
				memcpy(to,from,32) ;
			to += 32 ;
			from += 32 ;
			len -= 32 ;
			break ;
		case 'P' :		/* timestamp is NOT swapped */
			if (set) {
				to[0] = *from++ ;
				to[1] = *from++ ;
				to[2] = *from++ ;
				to[3] = *from++ ;
				to[4] = *from++ ;
				to[5] = *from++ ;
				to[6] = *from++ ;
				to[7] = *from++ ;
			}
			to += 8 ;
			len -= 8 ;
			break ;
		default :
			SMT_PANIC(smc,SMT_E0120, SMT_E0120_MSG) ;
			return SMT_RDF_ILLEGAL;
		}
	}
	/*
	 * actions and internal updates
	 */
	switch (pa->p_type) {
	case SMT_P101A:			/* fddiSMTConfigPolicy */
		if (word_val & ~1)
			goto val_error ;
		IFSET(mib->fddiSMTConfigPolicy = word_val) ;
		break ;
	case SMT_P101B :		/* fddiSMTConnectionPolicy */
		if (!(word_val & POLICY_MM))
			goto val_error ;
		IFSET(mib->fddiSMTConnectionPolicy = word_val) ;
		break ;
	case SMT_P101D : 		/* fddiSMTTT_Notify */
		if (word_val < 2 || word_val > 30)
			goto val_error ;
		IFSET(mib->fddiSMTTT_Notify = word_val) ;
		break ;
	case SMT_P101E :		/* fddiSMTStatRptPolicy */
		if (byte_val & ~1)
			goto val_error ;
		IFSET(mib->fddiSMTStatRptPolicy = byte_val) ;
		break ;
	case SMT_P101F :		/* fddiSMTTrace_MaxExpiration */
		/*
		 * note: lower limit trace_max = 6.001773... s
		 * NO upper limit
		 */
		if (long_val < (long)0x478bf51L)
			goto val_error ;
		IFSET(mib->fddiSMTTrace_MaxExpiration = long_val) ;
		break ;
#ifdef	ESS
	case SMT_P10F2 :		/* fddiESSPayload */
		if (long_val > 1562)
			goto val_error ;
		if (set && smc->mib.fddiESSPayload != long_val) {
			smc->ess.raf_act_timer_poll = TRUE ;
			smc->mib.fddiESSPayload = long_val ;
		}
		break ;
	case SMT_P10F3 :		/* fddiESSOverhead */
		if (long_val < 50 || long_val > 5000)
			goto val_error ;
		if (set && smc->mib.fddiESSPayload &&
			smc->mib.fddiESSOverhead != long_val) {
			smc->ess.raf_act_timer_poll = TRUE ;
			smc->mib.fddiESSOverhead = long_val ;
		}
		break ;
	case SMT_P10F4 :		/* fddiESSMaxTNeg */
		if (long_val > -MS2BCLK(5) || long_val < -MS2BCLK(165))
			goto val_error ;
		IFSET(mib->fddiESSMaxTNeg = long_val) ;
		break ;
	case SMT_P10F5 :		/* fddiESSMinSegmentSize */
		if (long_val < 1 || long_val > 4478)
			goto val_error ;
		IFSET(mib->fddiESSMinSegmentSize = long_val) ;
		break ;
	case SMT_P10F6 :		/* fddiESSCategory */
		if ((long_val & 0xffff) != 1)
			goto val_error ;
		IFSET(mib->fddiESSCategory = long_val) ;
		break ;
	case SMT_P10F7 :		/* fddiESSSyncTxMode */
		if (word_val > 1)
			goto val_error ;
		IFSET(mib->fddiESSSynchTxMode = word_val) ;
		break ;
#endif
#ifdef	SBA
	case SMT_P10F8 :		/* fddiSBACommand */
		if (byte_val != SB_STOP && byte_val != SB_START)
			goto val_error ;
		IFSET(mib->fddiSBACommand = byte_val) ;
		break ;
	case SMT_P10F9 :		/* fddiSBAAvailable */
		if (byte_val > 100)
			goto val_error ;
		IFSET(mib->fddiSBAAvailable = byte_val) ;
		break ;
#endif
	case SMT_P2020 :		/* fddiMACRequestedPaths */
		if ((word_val & (MIB_P_PATH_PRIM_PREFER |
			MIB_P_PATH_PRIM_ALTER)) == 0 )
			goto val_error ;
		IFSET(mib_m->fddiMACRequestedPaths = word_val) ;
		break ;
	case SMT_P205F :		/* fddiMACFrameErrorThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACFrameErrorThreshold = word_val) ;
		break ;
	case SMT_P2067 :		/* fddiMACNotCopiedThreshold */
		/* 0 .. ffff acceptable */
		IFSET(mib_m->fddiMACNotCopiedThreshold = word_val) ;
		break ;
	case SMT_P2076:			/* fddiMACMA_UnitdataEnable */
		if (byte_val & ~1)
			goto val_error ;
		if (set) {
			mib_m->fddiMACMA_UnitdataEnable = byte_val ;
			queue_event(smc,EVENT_RMT,RM_ENABLE_FLAG) ;
		}
		break ;
	case SMT_P20F1 :		/* fddiMACT_Min */
		IFSET(mib_m->fddiMACT_Min = long_val) ;
		break ;
	case SMT_P320F :
		if (long_val > 1562)
			goto val_error ;
		IFSET(mib_a->fddiPATHSbaPayload = long_val) ;
#ifdef	ESS
		if (set)
			ess_para_change(smc) ;
#endif
		break ;
	case SMT_P3210 :
		if (long_val > 5000)
			goto val_error ;
		
		if (long_val != 0 && mib_a->fddiPATHSbaPayload == 0)
			goto val_error ;

		IFSET(mib_a->fddiPATHSbaOverhead = long_val) ;
#ifdef	ESS
		if (set)
			ess_para_change(smc) ;
#endif
		break ;
	case SMT_P3213:			/* fddiPATHT_Rmode */
		/* no limit :
		 * 0 .. 343.597 => 0 .. 2e32 * 80nS
		 */
		if (set) {
			mib_a->fddiPATHT_Rmode = long_val ;
			rtm_set_timer(smc) ;
		}
		break ;
	case SMT_P3214 :		/* fddiPATHSbaAvailable */
		if (long_val > 0x00BEBC20L)
			goto val_error ;
#ifdef SBA 
		if (set && mib->fddiSBACommand == SB_STOP)
			goto val_error ;
#endif
		IFSET(mib_a->fddiPATHSbaAvailable = long_val) ;
		break ;
	case SMT_P3215 :		/* fddiPATHTVXLowerBound */
		IFSET(mib_a->fddiPATHTVXLowerBound = long_val) ;
		goto change_mac_para ;
	case SMT_P3216 :		/* fddiPATHT_MaxLowerBound */
		IFSET(mib_a->fddiPATHT_MaxLowerBound = long_val) ;
		goto change_mac_para ;
	case SMT_P3217 :		/* fddiPATHMaxT_Req */
		IFSET(mib_a->fddiPATHMaxT_Req = long_val) ;

change_mac_para:
		if (set && smt_set_mac_opvalues(smc)) {
			RS_SET(smc,RS_EVENT) ;
			smc->sm.please_reconnect = 1 ;
			queue_event(smc,EVENT_ECM,EC_DISCONNECT) ;
		}
		break ;
	case SMT_P400E :		/* fddiPORTConnectionPolicies */
		if (byte_val > 1)
			goto val_error ;
		IFSET(mib_p->fddiPORTConnectionPolicies = byte_val) ;
		break ;
	case SMT_P4011 :		/* fddiPORTRequestedPaths */
		/* all 3*8 bits allowed */
		IFSET(memcpy((char *)mib_p->fddiPORTRequestedPaths,
			(char *)&long_val,4)) ;
		break ;
	case SMT_P401F:			/* fddiPORTMaint_LS */
		if (word_val > 4)
			goto val_error ;
		IFSET(mib_p->fddiPORTMaint_LS = word_val) ;
		break ;
	case SMT_P403A :		/* fddiPORTLer_Cutoff */
		if (byte_val < 4 || byte_val > 15)
			goto val_error ;
		IFSET(mib_p->fddiPORTLer_Cutoff = byte_val) ;
		break ;
	case SMT_P403B :		/* fddiPORTLer_Alarm */
		if (byte_val < 4 || byte_val > 15)
			goto val_error ;
		IFSET(mib_p->fddiPORTLer_Alarm = byte_val) ;
		break ;

	/*
	 * Actions
	 */
	case SMT_P103C :		/* fddiSMTStationAction */
		if (smt_action(smc,SMT_STATION_ACTION, (int) word_val, 0))
			goto val_error ;
		break ;
	case SMT_P4046:			/* fddiPORTAction */
		if (smt_action(smc,SMT_PORT_ACTION, (int) word_val,
			port_to_mib(smc,port)))
			goto val_error ;
		break ;
	default :
		break ;
	}
	return 0;

val_error:
	/* parameter value in frame is out of range */
	return SMT_RDF_RANGE;

len_error:
	/* parameter value in frame is too short */
	return SMT_RDF_LENGTH;

#if	0
no_author_error:
	/* parameter not setable, because the SBA is not active
	 * Please note: we give the return code 'not authorizeed
	 *  because SBA denied is not a valid return code in the
	 * PMF protocol.
	 */
	return SMT_RDF_AUTHOR;
#endif
}