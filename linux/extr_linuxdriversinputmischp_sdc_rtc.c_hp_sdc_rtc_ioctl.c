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
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hp_sdc_rtc_ioctl(struct file *file, 
			    unsigned int cmd, unsigned long arg)
{
#if 1
	return -EINVAL;
#else
	
        struct rtc_time wtime; 
	struct timeval ttime;
	int use_wtime = 0;

	/* This needs major work. */

        switch (cmd) {

        case RTC_AIE_OFF:       /* Mask alarm int. enab. bit    */
        case RTC_AIE_ON:        /* Allow alarm interrupts.      */
	case RTC_PIE_OFF:       /* Mask periodic int. enab. bit */
        case RTC_PIE_ON:        /* Allow periodic ints          */
        case RTC_UIE_ON:        /* Allow ints for RTC updates.  */
        case RTC_UIE_OFF:       /* Allow ints for RTC updates.  */
        {
		/* We cannot mask individual user timers and we
		   cannot tell them apart when they occur, so it 
		   would be disingenuous to succeed these IOCTLs */
		return -EINVAL;
        }
        case RTC_ALM_READ:      /* Read the present alarm time */
        {
		if (hp_sdc_rtc_read_mt(&ttime)) return -EFAULT;
		if (hp_sdc_rtc_read_bbrtc(&wtime)) return -EFAULT;

		wtime.tm_hour = ttime.tv_sec / 3600;  ttime.tv_sec %= 3600;
		wtime.tm_min  = ttime.tv_sec / 60;    ttime.tv_sec %= 60;
		wtime.tm_sec  = ttime.tv_sec;
                
		break;
        }
        case RTC_IRQP_READ:     /* Read the periodic IRQ rate.  */
        {
                return put_user(hp_sdc_rtc_freq, (unsigned long *)arg);
        }
        case RTC_IRQP_SET:      /* Set periodic IRQ rate.       */
        {
                /* 
                 * The max we can do is 100Hz.
		 */

                if ((arg < 1) || (arg > 100)) return -EINVAL;
		ttime.tv_sec = 0;
		ttime.tv_usec = 1000000 / arg;
		if (hp_sdc_rtc_set_ct(&ttime)) return -EFAULT;
		hp_sdc_rtc_freq = arg;
                return 0;
        }
        case RTC_ALM_SET:       /* Store a time into the alarm */
        {
                /*
                 * This expects a struct hp_sdc_rtc_time. Writing 0xff means
                 * "don't care" or "match all" for PC timers.  The HP SDC
		 * does not support that perk, but it could be emulated fairly
		 * easily.  Only the tm_hour, tm_min and tm_sec are used.
		 * We could do it with 10ms accuracy with the HP SDC, if the 
		 * rtc interface left us a way to do that.
                 */
                struct hp_sdc_rtc_time alm_tm;

                if (copy_from_user(&alm_tm, (struct hp_sdc_rtc_time*)arg,
                                   sizeof(struct hp_sdc_rtc_time)))
                       return -EFAULT;

                if (alm_tm.tm_hour > 23) return -EINVAL;
		if (alm_tm.tm_min  > 59) return -EINVAL;
		if (alm_tm.tm_sec  > 59) return -EINVAL;  

		ttime.sec = alm_tm.tm_hour * 3600 + 
		  alm_tm.tm_min * 60 + alm_tm.tm_sec;
		ttime.usec = 0;
		if (hp_sdc_rtc_set_mt(&ttime)) return -EFAULT;
                return 0;
        }
        case RTC_RD_TIME:       /* Read the time/date from RTC  */
        {
		if (hp_sdc_rtc_read_bbrtc(&wtime)) return -EFAULT;
                break;
        }
        case RTC_SET_TIME:      /* Set the RTC */
        {
                struct rtc_time hp_sdc_rtc_tm;
                unsigned char mon, day, hrs, min, sec, leap_yr;
                unsigned int yrs;

                if (!capable(CAP_SYS_TIME))
                        return -EACCES;
		if (copy_from_user(&hp_sdc_rtc_tm, (struct rtc_time *)arg,
                                   sizeof(struct rtc_time)))
                        return -EFAULT;

                yrs = hp_sdc_rtc_tm.tm_year + 1900;
                mon = hp_sdc_rtc_tm.tm_mon + 1;   /* tm_mon starts at zero */
                day = hp_sdc_rtc_tm.tm_mday;
                hrs = hp_sdc_rtc_tm.tm_hour;
                min = hp_sdc_rtc_tm.tm_min;
                sec = hp_sdc_rtc_tm.tm_sec;

                if (yrs < 1970)
                        return -EINVAL;

                leap_yr = ((!(yrs % 4) && (yrs % 100)) || !(yrs % 400));

                if ((mon > 12) || (day == 0))
                        return -EINVAL;
                if (day > (days_in_mo[mon] + ((mon == 2) && leap_yr)))
                        return -EINVAL;
		if ((hrs >= 24) || (min >= 60) || (sec >= 60))
                        return -EINVAL;

                if ((yrs -= eH) > 255)    /* They are unsigned */
                        return -EINVAL;


                return 0;
        }
        case RTC_EPOCH_READ:    /* Read the epoch.      */
        {
                return put_user (epoch, (unsigned long *)arg);
        }
        case RTC_EPOCH_SET:     /* Set the epoch.       */
        {
                /* 
                 * There were no RTC clocks before 1900.
                 */
                if (arg < 1900)
		  return -EINVAL;
		if (!capable(CAP_SYS_TIME))
		  return -EACCES;
		
                epoch = arg;
                return 0;
        }
        default:
                return -EINVAL;
        }
        return copy_to_user((void *)arg, &wtime, sizeof wtime) ? -EFAULT : 0;
#endif
}