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
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PVR2_TRACE_DEBUGIFC ; 
 unsigned int debugifc_isolate_word (char const*,unsigned int,char const**,unsigned int*) ; 
 scalar_t__ debugifc_match_keyword (char const*,unsigned int,char*) ; 
 int debugifc_parse_unsigned_number (char const*,unsigned int,int*) ; 
 int pvr2_hdw_cmd_decoder_reset (struct pvr2_hdw*) ; 
 int pvr2_hdw_cmd_deep_reset (struct pvr2_hdw*) ; 
 int pvr2_hdw_cmd_powerup (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_cpufw_set_enabled (struct pvr2_hdw*,int,int) ; 
 int /*<<< orphan*/  pvr2_hdw_cpureset_assert (struct pvr2_hdw*,int) ; 
 int /*<<< orphan*/  pvr2_hdw_device_reset (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_hdw_get_video_stream (struct pvr2_hdw*) ; 
 int pvr2_hdw_gpio_chg_dir (struct pvr2_hdw*,int,int) ; 
 int pvr2_hdw_gpio_chg_out (struct pvr2_hdw*,int,int) ; 
 int pvr2_hdw_untrip (struct pvr2_hdw*) ; 
 int /*<<< orphan*/  pvr2_stream_get_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,unsigned int,char const*) ; 
 int pvr2_upload_firmware2 (struct pvr2_hdw*) ; 

__attribute__((used)) static int pvr2_debugifc_do1cmd(struct pvr2_hdw *hdw,const char *buf,
				unsigned int count)
{
	const char *wptr;
	unsigned int wlen;
	unsigned int scnt;

	scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
	if (!scnt) return 0;
	count -= scnt; buf += scnt;
	if (!wptr) return 0;

	pvr2_trace(PVR2_TRACE_DEBUGIFC,"debugifc cmd: \"%.*s\"",wlen,wptr);
	if (debugifc_match_keyword(wptr,wlen,"reset")) {
		scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
		if (!scnt) return -EINVAL;
		count -= scnt; buf += scnt;
		if (!wptr) return -EINVAL;
		if (debugifc_match_keyword(wptr,wlen,"cpu")) {
			pvr2_hdw_cpureset_assert(hdw,!0);
			pvr2_hdw_cpureset_assert(hdw,0);
			return 0;
		} else if (debugifc_match_keyword(wptr,wlen,"bus")) {
			pvr2_hdw_device_reset(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"soft")) {
			return pvr2_hdw_cmd_powerup(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"deep")) {
			return pvr2_hdw_cmd_deep_reset(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"firmware")) {
			return pvr2_upload_firmware2(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"decoder")) {
			return pvr2_hdw_cmd_decoder_reset(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"worker")) {
			return pvr2_hdw_untrip(hdw);
		} else if (debugifc_match_keyword(wptr,wlen,"usbstats")) {
			pvr2_stream_get_stats(pvr2_hdw_get_video_stream(hdw),
					      NULL, !0);
			return 0;
		}
		return -EINVAL;
	} else if (debugifc_match_keyword(wptr,wlen,"cpufw")) {
		scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
		if (!scnt) return -EINVAL;
		count -= scnt; buf += scnt;
		if (!wptr) return -EINVAL;
		if (debugifc_match_keyword(wptr,wlen,"fetch")) {
			scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
			if (scnt && wptr) {
				count -= scnt; buf += scnt;
				if (debugifc_match_keyword(wptr, wlen,
							   "prom")) {
					pvr2_hdw_cpufw_set_enabled(hdw, 2, !0);
				} else if (debugifc_match_keyword(wptr, wlen,
								  "ram8k")) {
					pvr2_hdw_cpufw_set_enabled(hdw, 0, !0);
				} else if (debugifc_match_keyword(wptr, wlen,
								  "ram16k")) {
					pvr2_hdw_cpufw_set_enabled(hdw, 1, !0);
				} else {
					return -EINVAL;
				}
			}
			pvr2_hdw_cpufw_set_enabled(hdw,0,!0);
			return 0;
		} else if (debugifc_match_keyword(wptr,wlen,"done")) {
			pvr2_hdw_cpufw_set_enabled(hdw,0,0);
			return 0;
		} else {
			return -EINVAL;
		}
	} else if (debugifc_match_keyword(wptr,wlen,"gpio")) {
		int dir_fl = 0;
		int ret;
		u32 msk,val;
		scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
		if (!scnt) return -EINVAL;
		count -= scnt; buf += scnt;
		if (!wptr) return -EINVAL;
		if (debugifc_match_keyword(wptr,wlen,"dir")) {
			dir_fl = !0;
		} else if (!debugifc_match_keyword(wptr,wlen,"out")) {
			return -EINVAL;
		}
		scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
		if (!scnt) return -EINVAL;
		count -= scnt; buf += scnt;
		if (!wptr) return -EINVAL;
		ret = debugifc_parse_unsigned_number(wptr,wlen,&msk);
		if (ret) return ret;
		scnt = debugifc_isolate_word(buf,count,&wptr,&wlen);
		if (wptr) {
			ret = debugifc_parse_unsigned_number(wptr,wlen,&val);
			if (ret) return ret;
		} else {
			val = msk;
			msk = 0xffffffff;
		}
		if (dir_fl) {
			ret = pvr2_hdw_gpio_chg_dir(hdw,msk,val);
		} else {
			ret = pvr2_hdw_gpio_chg_out(hdw,msk,val);
		}
		return ret;
	}
	pvr2_trace(PVR2_TRACE_DEBUGIFC,
		   "debugifc failed to recognize cmd: \"%.*s\"",wlen,wptr);
	return -EINVAL;
}