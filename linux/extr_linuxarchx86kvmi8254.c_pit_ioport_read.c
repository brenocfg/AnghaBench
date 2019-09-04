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
struct kvm_vcpu {int dummy; } ;
struct kvm_kpit_state {int /*<<< orphan*/  lock; struct kvm_kpit_channel_state* channels; } ;
struct kvm_pit {struct kvm_kpit_state pit_state; } ;
struct kvm_kpit_channel_state {int status; int count_latched; int latched_count; int read_state; scalar_t__ status_latched; } ;
struct kvm_io_device {int dummy; } ;
typedef  int /*<<< orphan*/  ret ;
typedef  int gpa_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int KVM_PIT_CHANNEL_MASK ; 
#define  RW_STATE_LSB 131 
#define  RW_STATE_MSB 130 
#define  RW_STATE_WORD0 129 
#define  RW_STATE_WORD1 128 
 struct kvm_pit* dev_to_pit (struct kvm_io_device*) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pit_get_count (struct kvm_pit*,int) ; 
 int /*<<< orphan*/  pit_in_range (int) ; 

__attribute__((used)) static int pit_ioport_read(struct kvm_vcpu *vcpu,
			   struct kvm_io_device *this,
			   gpa_t addr, int len, void *data)
{
	struct kvm_pit *pit = dev_to_pit(this);
	struct kvm_kpit_state *pit_state = &pit->pit_state;
	int ret, count;
	struct kvm_kpit_channel_state *s;
	if (!pit_in_range(addr))
		return -EOPNOTSUPP;

	addr &= KVM_PIT_CHANNEL_MASK;
	if (addr == 3)
		return 0;

	s = &pit_state->channels[addr];

	mutex_lock(&pit_state->lock);

	if (s->status_latched) {
		s->status_latched = 0;
		ret = s->status;
	} else if (s->count_latched) {
		switch (s->count_latched) {
		default:
		case RW_STATE_LSB:
			ret = s->latched_count & 0xff;
			s->count_latched = 0;
			break;
		case RW_STATE_MSB:
			ret = s->latched_count >> 8;
			s->count_latched = 0;
			break;
		case RW_STATE_WORD0:
			ret = s->latched_count & 0xff;
			s->count_latched = RW_STATE_MSB;
			break;
		}
	} else {
		switch (s->read_state) {
		default:
		case RW_STATE_LSB:
			count = pit_get_count(pit, addr);
			ret = count & 0xff;
			break;
		case RW_STATE_MSB:
			count = pit_get_count(pit, addr);
			ret = (count >> 8) & 0xff;
			break;
		case RW_STATE_WORD0:
			count = pit_get_count(pit, addr);
			ret = count & 0xff;
			s->read_state = RW_STATE_WORD1;
			break;
		case RW_STATE_WORD1:
			count = pit_get_count(pit, addr);
			ret = (count >> 8) & 0xff;
			s->read_state = RW_STATE_WORD0;
			break;
		}
	}

	if (len > sizeof(ret))
		len = sizeof(ret);
	memcpy(data, (char *)&ret, len);

	mutex_unlock(&pit_state->lock);
	return 0;
}