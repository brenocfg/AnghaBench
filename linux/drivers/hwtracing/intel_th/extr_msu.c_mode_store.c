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
struct msu_buffer {void* (* assign ) (struct device*,int*) ;} ;
struct msc {int mode; int /*<<< orphan*/  buf_mutex; struct msu_buffer const* mbuf; void* mbuf_priv; int /*<<< orphan*/  do_irq; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct msc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrndup (char const*,size_t,int /*<<< orphan*/ ) ; 
 int match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  msc_buffer_unassign (struct msc*) ; 
 int msc_buffer_unlocked_free_unless_used (struct msc*) ; 
 int /*<<< orphan*/  msc_mode ; 
 struct msu_buffer* msu_buffer_get (char*) ; 
 int /*<<< orphan*/  msu_buffer_put (struct msu_buffer const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* stub1 (struct device*,int*) ; 

__attribute__((used)) static ssize_t
mode_store(struct device *dev, struct device_attribute *attr, const char *buf,
	   size_t size)
{
	const struct msu_buffer *mbuf = NULL;
	struct msc *msc = dev_get_drvdata(dev);
	size_t len = size;
	char *cp, *mode;
	int i, ret;

	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	cp = memchr(buf, '\n', len);
	if (cp)
		len = cp - buf;

	mode = kstrndup(buf, len, GFP_KERNEL);
	if (!mode)
		return -ENOMEM;

	i = match_string(msc_mode, ARRAY_SIZE(msc_mode), mode);
	if (i >= 0) {
		kfree(mode);
		goto found;
	}

	/* Buffer sinks only work with a usable IRQ */
	if (!msc->do_irq) {
		kfree(mode);
		return -EINVAL;
	}

	mbuf = msu_buffer_get(mode);
	kfree(mode);
	if (mbuf)
		goto found;

	return -EINVAL;

found:
	mutex_lock(&msc->buf_mutex);
	ret = 0;

	/* Same buffer: do nothing */
	if (mbuf && mbuf == msc->mbuf) {
		/* put the extra reference we just got */
		msu_buffer_put(mbuf);
		goto unlock;
	}

	ret = msc_buffer_unlocked_free_unless_used(msc);
	if (ret)
		goto unlock;

	if (mbuf) {
		void *mbuf_priv = mbuf->assign(dev, &i);

		if (!mbuf_priv) {
			ret = -ENOMEM;
			goto unlock;
		}

		msc_buffer_unassign(msc);
		msc->mbuf_priv = mbuf_priv;
		msc->mbuf = mbuf;
	} else {
		msc_buffer_unassign(msc);
	}

	msc->mode = i;

unlock:
	if (ret && mbuf)
		msu_buffer_put(mbuf);
	mutex_unlock(&msc->buf_mutex);

	return ret ? ret : size;
}